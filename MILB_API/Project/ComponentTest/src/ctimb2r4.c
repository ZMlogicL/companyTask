/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-03
*@author              :liudong
*@brief               :CtImB2r4类
*@rely                :klib
*@function
*
*设计的主要功能:
*1、
*@version
*
*/

#include "ct_im_b2r.h"

#include "im_b2r.h"
#include "im_pro.h"
#include "im_pro_common.h"

#include "driver_common.h"
#include "ddim_user_custom.h"
#if defined(CO_ACT_CLOCK) || defined(CO_ACT_ICLOCK) || defined(CO_ACT_HCLOCK) || defined(CO_ACT_PCLOCK)
#include "dd_top.h"
#endif

#include "jdsb2r.h"

#include <stdlib.h>
#include <string.h>

#include "ctimb2r.h"

#include "ctimb2r4.h"
#include "ctimb2r1.h"

K_TYPE_DEFINE_WITH_PRIVATE(CtImB2r4, ct_im_b2r4);
#define CT_IM_B2R4_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o),CtImB2r4Private,CT_TYPE_IM_B2R4))


/*----------------------------------------------------------------------*/
/* Macro																*/
/*----------------------------------------------------------------------*/
#define ct_im_b2r_check_target_pipe_no_1(a)		(((a)+1) & (D_IM_B2R_PIPE1+1))
#define ct_im_b2r_check_target_pipe_no_2(a)		(((a)+1) & (D_IM_B2R_PIPE2+1))


struct _CtImB2r4Private
{

};

/*
DECLS
*/

static void ct_im_b2r4_constructor(CtImB2r4 *self) 
{
//	CtImB2r4Private *priv = CT_IM_B2R4_GET_PRIVATE(self);
}

static void ct_im_b2r4_destructor(CtImB2r4 *self) 
{
//	CtImB2r4Private *priv = CT_IM_B2R4_GET_PRIVATE(self);
	self = NULL;
}

/*
IMPL//todo
*/

/*
PUBLIC//todo
*/

#undef D_IM_B2R_FUNC_NAME
#define D_IM_B2R_FUNC_NAME "ct_im_b2r4_1_38: "
kint32 ct_im_b2r4_1_38( CtImB2r4 *self )
{
	UCHAR access_enable[] = {
		[0] = 1,	// max
		[1] = 0,	// min
	};
	kuint32 loopcnt;
#ifdef CO_MSG_PRINT_ON
	kint32 ercd;
#endif

	Ddim_Print(( "%s\n", D_IM_B2R_FUNC_NAME ));

#ifdef CO_MSG_PRINT_ON
	Im_B2R_Init( D_IM_B2R_PIPE12 );
	Ddim_Print(( "Initial value\n" ));
	Im_B2R_On_Pclk( D_IM_B2R_PIPE12 );
	Ddim_Print(( "IO_B2R_P1.B2R_CMN.RAMAEN.word                = 0x%lx\n", IO_B2R_P1.B2R_CMN.RAMAEN.word ));
	Ddim_Print(( "IO_B2R_P1.B2R_CMN.RAMAEN.bit.RAMAEN_RGB_KNEE = %u\n",    IO_B2R_P1.B2R_CMN.RAMAEN.bit.RAMAEN_RGB_KNEE ));
	Ddim_Print(( "IO_B2R_P2.B2R_CMN.RAMAEN.word                = 0x%lx\n", IO_B2R_P2.B2R_CMN.RAMAEN.word ));
	Ddim_Print(( "IO_B2R_P2.B2R_CMN.RAMAEN.bit.RAMAEN_RGB_KNEE = %u\n",    IO_B2R_P2.B2R_CMN.RAMAEN.bit.RAMAEN_RGB_KNEE ));
	Im_B2R_Off_Pclk( D_IM_B2R_PIPE12 );
#endif

	for( loopcnt = 0; loopcnt < (sizeof(access_enable) / sizeof(access_enable[0])); loopcnt++ ) {
		Ddim_Print(( "** %u\n", loopcnt ));

#ifdef CO_MSG_PRINT_ON
		ercd = Im_B2R_Set_RGB_KneeAccessEnable( self->pipeNo, access_enable[loopcnt], D_IM_B2R_WAIT_ON );
		Ddim_Print(( D_IM_B2R_FUNC_NAME "0x%x\n", ercd ));
		Im_B2R_On_Pclk( D_IM_B2R_PIPE12 );
		Ddim_Print(( "IO_B2R_P1.B2R_CMN.RAMAEN.word                = 0x%lx\n", IO_B2R_P1.B2R_CMN.RAMAEN.word ));
		Ddim_Print(( "IO_B2R_P1.B2R_CMN.RAMAEN.bit.RAMAEN_RGB_KNEE = %u\n",    IO_B2R_P1.B2R_CMN.RAMAEN.bit.RAMAEN_RGB_KNEE ));
		Ddim_Print(( "IO_B2R_P2.B2R_CMN.RAMAEN.word                = 0x%lx\n", IO_B2R_P2.B2R_CMN.RAMAEN.word ));
		Ddim_Print(( "IO_B2R_P2.B2R_CMN.RAMAEN.bit.RAMAEN_RGB_KNEE = %u\n",    IO_B2R_P2.B2R_CMN.RAMAEN.bit.RAMAEN_RGB_KNEE ));
		Im_B2R_Off_Pclk( D_IM_B2R_PIPE12 );
#endif
	}


	return D_DDIM_OK;
}

#undef D_IM_B2R_FUNC_NAME
#define D_IM_B2R_FUNC_NAME "ct_im_b2r4_1_39: "
kint32 ct_im_b2r4_1_39( CtImB2r4 *self )
{
	T_IM_B2R_OFS ofs[] = {
		[0] = {	// max
			.R = 0x1FF,
			.B = 0x1FF,
			.Gr = 0x1FF,
			.Gb = 0x1FF,
		},
		[1] = {	// max
			.R = -1,
			.B = -1,
			.Gr = -1,
			.Gb = -1,
		},
		[2] = {	// min
			.R = 0,
			.B = 0,
			.Gr = 0,
			.Gb = 0,
		},
		[3] = {	// indvisual
			.R = 1,
			.B = 2,
			.Gr = 3,
			.Gb = 4,
		},
	};
	kuint32 loopcnt;
#ifdef CO_MSG_PRINT_ON
	kint32 ercd;
#endif

	Ddim_Print(( "%s\n", D_IM_B2R_FUNC_NAME ));


	for( loopcnt = 0; loopcnt < (sizeof(ofs) / sizeof(ofs[0])); loopcnt++ ) {
		Ddim_Print(( "** %u\n", loopcnt ));

#ifdef CO_MSG_PRINT_ON
		ercd = Im_B2R_Set_Offset( self->pipeNo, &ofs[loopcnt] );
		Ddim_Print(( D_IM_B2R_FUNC_NAME "0x%x\n", ercd ));
		Im_B2R_On_Pclk( D_IM_B2R_PIPE12 );
		Ddim_Print(( "IO_B2R_P1.F_B2R.OFSTRB.word       = 0x%lx\n", IO_B2R_P1.F_B2R.OFG.OFSTRB.word ));
		Ddim_Print(( "IO_B2R_P1.F_B2R.OFSTRB.bit.OFSTRR = 0x%x\n",  IO_B2R_P1.F_B2R.OFG.OFSTRB.bit.OFSTRR ));
		Ddim_Print(( "IO_B2R_P1.F_B2R.OFSTRB.bit.OFSTBB = 0x%x\n",  IO_B2R_P1.F_B2R.OFG.OFSTRB.bit.OFSTBB ));
		Ddim_Print(( "IO_B2R_P1.F_B2R.OFSTG.word        = 0x%lx\n", IO_B2R_P1.F_B2R.OFG.OFSTG.word ));
		Ddim_Print(( "IO_B2R_P1.F_B2R.OFSTG.bit.OFSTGR  = 0x%x\n",  IO_B2R_P1.F_B2R.OFG.OFSTG.bit.OFSTGR ));
		Ddim_Print(( "IO_B2R_P1.F_B2R.OFSTG.bit.OFSTGB  = 0x%x\n",  IO_B2R_P1.F_B2R.OFG.OFSTG.bit.OFSTGB ));
		Ddim_Print(( "IO_B2R_P2.F_B2R.OFSTRB.word       = 0x%lx\n", IO_B2R_P2.F_B2R.OFG.OFSTRB.word ));
		Ddim_Print(( "IO_B2R_P2.F_B2R.OFSTRB.bit.OFSTRR = 0x%x\n",  IO_B2R_P2.F_B2R.OFG.OFSTRB.bit.OFSTRR ));
		Ddim_Print(( "IO_B2R_P2.F_B2R.OFSTRB.bit.OFSTBB = 0x%x\n",  IO_B2R_P2.F_B2R.OFG.OFSTRB.bit.OFSTBB ));
		Ddim_Print(( "IO_B2R_P2.F_B2R.OFSTG.word        = 0x%lx\n", IO_B2R_P2.F_B2R.OFG.OFSTG.word ));
		Ddim_Print(( "IO_B2R_P2.F_B2R.OFSTG.bit.OFSTGR  = 0x%x\n",  IO_B2R_P2.F_B2R.OFG.OFSTG.bit.OFSTGR ));
		Ddim_Print(( "IO_B2R_P2.F_B2R.OFSTG.bit.OFSTGB  = 0x%x\n",  IO_B2R_P2.F_B2R.OFG.OFSTG.bit.OFSTGB ));
		Im_B2R_Off_Pclk( D_IM_B2R_PIPE12 );
#endif
	}


	return D_DDIM_OK;
}

#undef D_IM_B2R_FUNC_NAME
#define D_IM_B2R_FUNC_NAME "ct_im_b2r4_1_40: "
kint32 ct_im_b2r4_1_40( CtImB2r4 *self )
{
	UCHAR bayer_left_shift[] = {
		[0] = 3,	// max
		[1] = 0,	// min
	};
	UCHAR saturation_mode[] = {
		[0] = D_IM_B2R_ENABLE_ON,
		[1] = D_IM_B2R_ENABLE_OFF,
	};
	kuint32 loopcnt;
#ifdef CO_MSG_PRINT_ON
	kint32 ercd;
#endif

	Ddim_Print(( "%s\n", D_IM_B2R_FUNC_NAME ));


	for( loopcnt = 0; loopcnt < (sizeof(bayer_left_shift) / sizeof(bayer_left_shift[0])); loopcnt++ ) {
		Ddim_Print(( "** %u\n", loopcnt ));

#ifdef CO_MSG_PRINT_ON
		ercd = Im_B2R_Ctrl_Left_Shift( self->pipeNo, bayer_left_shift[loopcnt], saturation_mode[loopcnt] );
		Ddim_Print(( D_IM_B2R_FUNC_NAME "0x%x\n", ercd ));
		Im_B2R_On_Pclk( D_IM_B2R_PIPE12 );
		Ddim_Print(( D_IM_B2R_FUNC_NAME "IO_B2R_P1.F_B2R.OFG.BLSFT.bit.BLSFT  = %u\n", IO_B2R_P1.F_B2R.OFG.BLSFT.bit.BLSFT ));
		Ddim_Print(( D_IM_B2R_FUNC_NAME "IO_B2R_P2.F_B2R.OFG.BLSFT.bit.BLSFT  = %u\n", IO_B2R_P2.F_B2R.OFG.BLSFT.bit.BLSFT ));
		Ddim_Print(( D_IM_B2R_FUNC_NAME "IO_B2R_P1.F_B2R.OFG.BLSFT.bit.BLSFMD = %u\n", IO_B2R_P1.F_B2R.OFG.BLSFT.bit.BLSFMD ));
		Ddim_Print(( D_IM_B2R_FUNC_NAME "IO_B2R_P2.F_B2R.OFG.BLSFT.bit.BLSFMD = %u\n", IO_B2R_P2.F_B2R.OFG.BLSFT.bit.BLSFMD ));
		Im_B2R_Off_Pclk( D_IM_B2R_PIPE12 );
#endif
	}


	return D_DDIM_OK;
}

#undef D_IM_B2R_FUNC_NAME
#define D_IM_B2R_FUNC_NAME "ct_im_b2r4_1_41: "
kint32 ct_im_b2r4_1_41( CtImB2r4 *self )
{
	T_IM_B2R_BAYER_COLOR b2r_bay_color[] = {
		[0] = {	// max
			.R = 0x7FF,
			.B = 0x7FF,
			.Gr = 0x7FF,
			.Gb = 0x7FF,
		},
		[1] = {	// min
			.R = 0,
			.B = 0,
			.Gr = 0,
			.Gb = 0,
		},
		[2] = {	// indvisual
			.R = 1,
			.B = 2,
			.Gr = 3,
			.Gb = 4,
		}
	};
#ifdef CO_MSG_PRINT_ON
	kint32 ercd;
#endif
	kuint32 loopcnt;

	Ddim_Print(( "%s\n", D_IM_B2R_FUNC_NAME ));


	for( loopcnt = 0; loopcnt < (sizeof(b2r_bay_color) / sizeof(b2r_bay_color[0])); loopcnt++ ) {
		Ddim_Print(( "** %u\n", loopcnt ));

#ifdef CO_MSG_PRINT_ON
		ercd = Im_B2R_Set_WB_Gain( self->pipeNo, &b2r_bay_color[loopcnt] );
		Ddim_Print(( D_IM_B2R_FUNC_NAME "0x%x\n", ercd ));
		Im_B2R_On_Pclk( D_IM_B2R_PIPE12 );
		Ddim_Print(( D_IM_B2R_FUNC_NAME "IO_B2R_P1.F_B2R.OFG.WBGARB.bit.WBGARR = 0x%x\n", IO_B2R_P1.F_B2R.OFG.WBGARB.bit.WBGARR ));
		Ddim_Print(( D_IM_B2R_FUNC_NAME "IO_B2R_P1.F_B2R.OFG.WBGARB.bit.WBGABB = 0x%x\n", IO_B2R_P1.F_B2R.OFG.WBGARB.bit.WBGABB ));
		Ddim_Print(( D_IM_B2R_FUNC_NAME "IO_B2R_P1.F_B2R.OFG.WBGAGR.bit.WBGAGR = 0x%x\n", IO_B2R_P1.F_B2R.OFG.WBGAGR.bit.WBGAGR ));
		Ddim_Print(( D_IM_B2R_FUNC_NAME "IO_B2R_P1.F_B2R.OFG.WBGAGR.bit.WBGAGB = 0x%x\n", IO_B2R_P1.F_B2R.OFG.WBGAGR.bit.WBGAGB ));
		Ddim_Print(( D_IM_B2R_FUNC_NAME "IO_B2R_P2.F_B2R.OFG.WBGARB.bit.WBGARR = 0x%x\n", IO_B2R_P2.F_B2R.OFG.WBGARB.bit.WBGARR ));
		Ddim_Print(( D_IM_B2R_FUNC_NAME "IO_B2R_P2.F_B2R.OFG.WBGARB.bit.WBGABB = 0x%x\n", IO_B2R_P2.F_B2R.OFG.WBGARB.bit.WBGABB ));
		Ddim_Print(( D_IM_B2R_FUNC_NAME "IO_B2R_P2.F_B2R.OFG.WBGAGR.bit.WBGAGR = 0x%x\n", IO_B2R_P2.F_B2R.OFG.WBGAGR.bit.WBGAGR ));
		Ddim_Print(( D_IM_B2R_FUNC_NAME "IO_B2R_P2.F_B2R.OFG.WBGAGR.bit.WBGAGB = 0x%x\n", IO_B2R_P2.F_B2R.OFG.WBGAGR.bit.WBGAGB ));
		Im_B2R_Off_Pclk( D_IM_B2R_PIPE12 );
#endif
	}


	return D_DDIM_OK;
}

#undef D_IM_B2R_FUNC_NAME
#define D_IM_B2R_FUNC_NAME "ct_im_b2r4_1_42: "
kint32 ct_im_b2r4_1_42( CtImB2r4 *self )
{
	T_IM_B2R_BAYER_COLOR b2r_bay_color[] = {
		[0] = {	// max
			.R = 0xFFF,
			.B = 0xFFF,
			.Gr = 0xFFF,
			.Gb = 0xFFF,
		},
		[1] = {	// min
			.R = 0,
			.B = 0,
			.Gr = 0,
			.Gb = 0,
		},
		[2] = {	// indvisual
			.R = 1,
			.B = 2,
			.Gr = 3,
			.Gb = 4,
		}
	};
#ifdef CO_MSG_PRINT_ON
	kint32 ercd;
#endif
	kuint32 loopcnt;

	Ddim_Print(( "%s\n", D_IM_B2R_FUNC_NAME ));


	for( loopcnt = 0; loopcnt < (sizeof(b2r_bay_color) / sizeof(b2r_bay_color[0])); loopcnt++ ) {
		Ddim_Print(( "** %u\n", loopcnt ));

#ifdef CO_MSG_PRINT_ON
		ercd = Im_B2R_Set_WB_Slope_Gain( self->pipeNo, (loopcnt & 1), &b2r_bay_color[loopcnt] );
		Ddim_Print(( D_IM_B2R_FUNC_NAME "0x%x\n", ercd ));
		Im_B2R_On_Pclk( D_IM_B2R_PIPE12 );
		Ddim_Print(( D_IM_B2R_FUNC_NAME "IO_B2R_P1.F_B2R.OFG.WBHCTL.bit.WBHCEN = 0x%x\n", IO_B2R_P1.F_B2R.OFG.WBHCTL.bit.WBHCEN ));
		Ddim_Print(( D_IM_B2R_FUNC_NAME "IO_B2R_P1.F_B2R.OFG.WBSLP.bit.WBSLPRR = 0x%x\n", IO_B2R_P1.F_B2R.OFG.WBSLP.bit.WBSLPRR ));
		Ddim_Print(( D_IM_B2R_FUNC_NAME "IO_B2R_P1.F_B2R.OFG.WBSLP.bit.WBSLPBB = 0x%x\n", IO_B2R_P1.F_B2R.OFG.WBSLP.bit.WBSLPBB ));
		Ddim_Print(( D_IM_B2R_FUNC_NAME "IO_B2R_P1.F_B2R.OFG.WBSLP.bit.WBSLPGR = 0x%x\n", IO_B2R_P1.F_B2R.OFG.WBSLP.bit.WBSLPGR ));
		Ddim_Print(( D_IM_B2R_FUNC_NAME "IO_B2R_P1.F_B2R.OFG.WBSLP.bit.WBSLPGB = 0x%x\n", IO_B2R_P1.F_B2R.OFG.WBSLP.bit.WBSLPGB ));
		Ddim_Print(( D_IM_B2R_FUNC_NAME "IO_B2R_P2.F_B2R.OFG.WBHCTL.bit.WBHCEN = 0x%x\n", IO_B2R_P2.F_B2R.OFG.WBHCTL.bit.WBHCEN ));
		Ddim_Print(( D_IM_B2R_FUNC_NAME "IO_B2R_P2.F_B2R.OFG.WBSLP.bit.WBSLPRR = 0x%x\n", IO_B2R_P2.F_B2R.OFG.WBSLP.bit.WBSLPRR ));
		Ddim_Print(( D_IM_B2R_FUNC_NAME "IO_B2R_P2.F_B2R.OFG.WBSLP.bit.WBSLPBB = 0x%x\n", IO_B2R_P2.F_B2R.OFG.WBSLP.bit.WBSLPBB ));
		Ddim_Print(( D_IM_B2R_FUNC_NAME "IO_B2R_P2.F_B2R.OFG.WBSLP.bit.WBSLPGR = 0x%x\n", IO_B2R_P2.F_B2R.OFG.WBSLP.bit.WBSLPGR ));
		Ddim_Print(( D_IM_B2R_FUNC_NAME "IO_B2R_P2.F_B2R.OFG.WBSLP.bit.WBSLPGB = 0x%x\n", IO_B2R_P2.F_B2R.OFG.WBSLP.bit.WBSLPGB ));
		Im_B2R_Off_Pclk( D_IM_B2R_PIPE12 );
#endif
	}


	return D_DDIM_OK;
}

#undef D_IM_B2R_FUNC_NAME
#define D_IM_B2R_FUNC_NAME "ct_im_b2r4_1_43: "
kint32 ct_im_b2r4_1_43( CtImB2r4 *self )
{
	T_IM_B2R_BAYER_COLOR b2r_bay_color[] = {
		[0] = {	// max
			.R = 0xFFF,
			.B = 0xFFF,
			.Gr = 0xFFF,
			.Gb = 0xFFF,
		},
		[1] = {	// min
			.R = 0,
			.B = 0,
			.Gr = 0,
			.Gb = 0,
		},
		[2] = {	// indvisual
			.R = 1,
			.B = 2,
			.Gr = 3,
			.Gb = 4,
		}
	};
#ifdef CO_MSG_PRINT_ON
	kint32 ercd;
#endif
	kuint32 loopcnt;

	Ddim_Print(( "%s\n", D_IM_B2R_FUNC_NAME ));


	for( loopcnt = 0; loopcnt < (sizeof(b2r_bay_color) / sizeof(b2r_bay_color[0])); loopcnt++ ) {
		Ddim_Print(( "** %u\n", loopcnt ));

#ifdef CO_MSG_PRINT_ON
		ercd = Im_B2R_Set_WB_Clip_Level( self->pipeNo, &b2r_bay_color[loopcnt] );
		Ddim_Print(( D_IM_B2R_FUNC_NAME "0x%x\n", ercd ));
		Im_B2R_On_Pclk( D_IM_B2R_PIPE12 );
		Ddim_Print(( D_IM_B2R_FUNC_NAME "IO_B2R_P1.F_B2R.OFG.WBLVRB.bit.WBLVRR = 0x%x\n", IO_B2R_P1.F_B2R.OFG.WBLVRB.bit.WBLVRR ));
		Ddim_Print(( D_IM_B2R_FUNC_NAME "IO_B2R_P1.F_B2R.OFG.WBLVRB.bit.WBLVBB = 0x%x\n", IO_B2R_P1.F_B2R.OFG.WBLVRB.bit.WBLVBB ));
		Ddim_Print(( D_IM_B2R_FUNC_NAME "IO_B2R_P1.F_B2R.OFG.WBLVGR.bit.WBLVGR = 0x%x\n", IO_B2R_P1.F_B2R.OFG.WBLVGR.bit.WBLVGR ));
		Ddim_Print(( D_IM_B2R_FUNC_NAME "IO_B2R_P1.F_B2R.OFG.WBLVGR.bit.WBLVGB = 0x%x\n", IO_B2R_P1.F_B2R.OFG.WBLVGR.bit.WBLVGB ));
		Ddim_Print(( D_IM_B2R_FUNC_NAME "IO_B2R_P2.F_B2R.OFG.WBLVRB.bit.WBLVRR = 0x%x\n", IO_B2R_P2.F_B2R.OFG.WBLVRB.bit.WBLVRR ));
		Ddim_Print(( D_IM_B2R_FUNC_NAME "IO_B2R_P2.F_B2R.OFG.WBLVRB.bit.WBLVBB = 0x%x\n", IO_B2R_P2.F_B2R.OFG.WBLVRB.bit.WBLVBB ));
		Ddim_Print(( D_IM_B2R_FUNC_NAME "IO_B2R_P2.F_B2R.OFG.WBLVGR.bit.WBLVGR = 0x%x\n", IO_B2R_P2.F_B2R.OFG.WBLVGR.bit.WBLVGR ));
		Ddim_Print(( D_IM_B2R_FUNC_NAME "IO_B2R_P2.F_B2R.OFG.WBLVGR.bit.WBLVGB = 0x%x\n", IO_B2R_P2.F_B2R.OFG.WBLVGR.bit.WBLVGB ));
		Im_B2R_Off_Pclk( D_IM_B2R_PIPE12 );
#endif
	}


	return D_DDIM_OK;
}

#undef D_IM_B2R_FUNC_NAME
#define D_IM_B2R_FUNC_NAME "ct_im_b2r4_1_44: "
kint32 ct_im_b2r4_1_44( CtImB2r4 *self )
{
	T_IM_B2R_CTRL_ADIP b2r_ctrl_adip[] = {
		[0] = {	// max
			.sharp_level_a = 0xF,
			.sharp_level_b = 0xF,
			.sharp_level_c = 0xF,
			.adj_feel_a = 0xF,
			.adj_feel_b = 0xFF,
			.lf_strength = 0x10,
			.lf_threshold = 0x3FF,
			.cmc_level = 0x4,
			.cmc_limit = 0x3FF,
			.dir_reliab_threshold = 0xFFF,
		},
		[1] = {	// min
			.sharp_level_a = 0,
			.sharp_level_b = 0,
			.sharp_level_c = 0,
			.adj_feel_a = 0,
			.adj_feel_b = 0,
			.lf_strength = 0,
			.lf_threshold = 0,
			.cmc_level = 0,
			.cmc_limit = 0,
			.dir_reliab_threshold = 0,
		},
		[2] = {	// ind
			.sharp_level_a = 10,
			.sharp_level_b = 9,
			.sharp_level_c = 8,
			.adj_feel_a = 7,
			.adj_feel_b = 6,
			.lf_strength = 5,
			.lf_threshold = 4,
			.cmc_level = 3,
			.cmc_limit = 2,
			.dir_reliab_threshold = 1,
		},
	};
#ifdef CO_MSG_PRINT_ON
	kint32 ercd;
#endif
	kuint32 loopcnt;

	Ddim_Print(( "%s\n", D_IM_B2R_FUNC_NAME ));



	for( loopcnt = 0; loopcnt < (sizeof(b2r_ctrl_adip) / sizeof(b2r_ctrl_adip[0])); loopcnt++ ) {
		Ddim_Print(( "** %u\n", loopcnt ));

#ifdef CO_MSG_PRINT_ON
		ercd = Im_B2R_Ctrl_Sensitivity( self->pipeNo, &b2r_ctrl_adip[loopcnt] );
		Ddim_Print(( D_IM_B2R_FUNC_NAME "0x%x\n", ercd ));
		Im_B2R_On_Pclk( D_IM_B2R_PIPE12 );
		Ddim_Print(( D_IM_B2R_FUNC_NAME "IO_B2R_P1.F_B2R.CIA.SHARP.bit.SHARPA      = 0x%x\n", IO_B2R_P1.F_B2R.CIA.SHARP.bit.SHARPA ));
		Ddim_Print(( D_IM_B2R_FUNC_NAME "IO_B2R_P1.F_B2R.CIA.SHARP.bit.SHARPB      = 0x%x\n", IO_B2R_P1.F_B2R.CIA.SHARP.bit.SHARPB ));
		Ddim_Print(( D_IM_B2R_FUNC_NAME "IO_B2R_P1.F_B2R.CIA.SHARP.bit.SHARPC      = 0x%x\n", IO_B2R_P1.F_B2R.CIA.SHARP.bit.SHARPC ));
		Ddim_Print(( D_IM_B2R_FUNC_NAME "IO_B2R_P1.F_B2R.CIA.AIRESY.bit.AIRESYA    = 0x%x\n", IO_B2R_P1.F_B2R.CIA.AIRESY.bit.AIRESYA ));
		Ddim_Print(( D_IM_B2R_FUNC_NAME "IO_B2R_P1.F_B2R.CIA.AIRESY.bit.AIRESYB    = 0x%x\n", IO_B2R_P1.F_B2R.CIA.AIRESY.bit.AIRESYB ));
		Ddim_Print(( D_IM_B2R_FUNC_NAME "IO_B2R_P1.F_B2R.CIA.LF.bit.LFSTR          = 0x%x\n", IO_B2R_P1.F_B2R.CIA.LF.bit.LFSTR ));
		Ddim_Print(( D_IM_B2R_FUNC_NAME "IO_B2R_P1.F_B2R.CIA.LF.bit.LFTH           = 0x%x\n", IO_B2R_P1.F_B2R.CIA.LF.bit.LFTH ));
		Ddim_Print(( D_IM_B2R_FUNC_NAME "IO_B2R_P1.F_B2R.CIA.CMC.bit.CMCSCL        = 0x%x\n", IO_B2R_P1.F_B2R.CIA.CMC.bit.CMCSCL ));
		Ddim_Print(( D_IM_B2R_FUNC_NAME "IO_B2R_P1.F_B2R.CIA.CMC.bit.CMCLMT        = 0x%x\n", IO_B2R_P1.F_B2R.CIA.CMC.bit.CMCLMT ));
		Ddim_Print(( D_IM_B2R_FUNC_NAME "IO_B2R_P1.F_B2R.CIA.DIRRLITH.bit.DIRRLITH = 0x%x\n", IO_B2R_P1.F_B2R.CIA.DIRRLITH.bit.DIRRLITH ));
		Ddim_Print(( D_IM_B2R_FUNC_NAME "IO_B2R_P2.F_B2R.CIA.SHARP.bit.SHARPA      = 0x%x\n", IO_B2R_P2.F_B2R.CIA.SHARP.bit.SHARPA ));
		Ddim_Print(( D_IM_B2R_FUNC_NAME "IO_B2R_P2.F_B2R.CIA.SHARP.bit.SHARPB      = 0x%x\n", IO_B2R_P2.F_B2R.CIA.SHARP.bit.SHARPB ));
		Ddim_Print(( D_IM_B2R_FUNC_NAME "IO_B2R_P2.F_B2R.CIA.SHARP.bit.SHARPC      = 0x%x\n", IO_B2R_P2.F_B2R.CIA.SHARP.bit.SHARPC ));
		Ddim_Print(( D_IM_B2R_FUNC_NAME "IO_B2R_P2.F_B2R.CIA.AIRESY.bit.AIRESYA    = 0x%x\n", IO_B2R_P2.F_B2R.CIA.AIRESY.bit.AIRESYA ));
		Ddim_Print(( D_IM_B2R_FUNC_NAME "IO_B2R_P2.F_B2R.CIA.AIRESY.bit.AIRESYB    = 0x%x\n", IO_B2R_P2.F_B2R.CIA.AIRESY.bit.AIRESYB ));
		Ddim_Print(( D_IM_B2R_FUNC_NAME "IO_B2R_P2.F_B2R.CIA.LF.bit.LFSTR          = 0x%x\n", IO_B2R_P2.F_B2R.CIA.LF.bit.LFSTR ));
		Ddim_Print(( D_IM_B2R_FUNC_NAME "IO_B2R_P2.F_B2R.CIA.LF.bit.LFTH           = 0x%x\n", IO_B2R_P2.F_B2R.CIA.LF.bit.LFTH ));
		Ddim_Print(( D_IM_B2R_FUNC_NAME "IO_B2R_P2.F_B2R.CIA.CMC.bit.CMCSCL        = 0x%x\n", IO_B2R_P2.F_B2R.CIA.CMC.bit.CMCSCL ));
		Ddim_Print(( D_IM_B2R_FUNC_NAME "IO_B2R_P2.F_B2R.CIA.CMC.bit.CMCLMT        = 0x%x\n", IO_B2R_P2.F_B2R.CIA.CMC.bit.CMCLMT ));
		Ddim_Print(( D_IM_B2R_FUNC_NAME "IO_B2R_P2.F_B2R.CIA.DIRRLITH.bit.DIRRLITH = 0x%x\n", IO_B2R_P2.F_B2R.CIA.DIRRLITH.bit.DIRRLITH ));
		Im_B2R_Off_Pclk( D_IM_B2R_PIPE12 );
#endif
	}


	return D_DDIM_OK;
}


#undef D_IM_B2R_FUNC_NAME
#define D_IM_B2R_FUNC_NAME "ct_im_b2r4_1_45: "
kint32 ct_im_b2r4_1_45( CtImB2r4 *self )
{
	T_IM_B2R_CTRL_HPF b2r_ctrl_hpf[] = {
		[0] = {	// max
			.hpf_enable = 1,
			.flat_ctrl_enable = 1,
			.y_ctrl_enable = 1,
			.hpf_k = {
				0x3FF,	// 0
				-1,	// 1
				-1,	// 2
				-1,	// 3
				-1,	// 4
				-1,	// 5
				-1,	// 6
				-1,	// 7
				-1,	// 8
				-1,	// 9
			},
			.hpf_level_clip_p = 0x1FF,
			.hpf_level_clip_m = 0x1FF,
			.flat_scale = 0xF,
			.flat_threshold = 0xFFF,
			.flat_gain_limit = 0xFFF,
			.flat_level_clip_p = 0x1FF,
			.flat_level_clip_m = 0x1FF,
			.y_convert_coef = {
				0xFF, 0xFF, 0xFF,
				  -1,   -1,   -1,
				  -1,   -1,   -1,
			},
			.y_ctrl_offset = {
				0xFFF, 0xFFF, 0xFFF, 0xFFF,
			},
			.y_ctrl_gain = {
				-1, -1, -1, -1,
			},
			.y_ctrl_border = {
				0xFFF, 0xFFF, 0xFFF, 0xFFF,
			},
			.y_ctrl_gain_posi_dec1 = 0x7,
			.y_ctrl_gain_posi_dec2 = 0xF,
			.y_ctrl_level_clip_p = 0x1FF,
			.y_ctrl_level_clip_m = 0x1FF,
			.y_ctrl_cor_p = 0x3F,
			.y_ctrl_cor_m = 0x3F,
			.hpf_add_level_clip_r = 0xFFF,
			.hpf_add_level_clip_g = 0xFFF,
			.hpf_add_level_clip_b = 0xFFF,
			.area_a_enable = 1,
			.area_b_enable = 1,
			.area_marge_method = 2,
			.area_a_ctrl = {
				.ellipse_area_focus1_x = -1,
				.ellipse_area_focus1_y = -1,
				.ellipse_area_focus2_x = -1,
				.ellipse_area_focus2_y = -1,
				.c_area_scale_offset = 0xFF,
				.c_area_scale_gain = {
					-1, -1,
				},
				.c_area_scale_border = 0x7F,
				.c_area_scale_clip_l = 0xFF,
				.c_area_scale_clip_h = 0xFF,
				.y_area_scale_gain = {
					0xFF, 0xFF,
				},
				.y_area_scale_border = {
					0xFFF, 0xFFF,
				},
				.y_area_scale_clip_l = 0x1FF,
				.y_area_scale_clip_h = 0x1FF,
			},
			.area_b_ctrl = {
				.ellipse_area_focus1_x = -1,
				.ellipse_area_focus1_y = -1,
				.ellipse_area_focus2_x = -1,
				.ellipse_area_focus2_y = -1,
				.c_area_scale_offset = 0xFF,
				.c_area_scale_gain = {
					-1, -1,
				},
				.c_area_scale_border = 0x7F,
				.c_area_scale_clip_l = 0xFF,
				.c_area_scale_clip_h = 0xFF,
				.y_area_scale_gain = {
					0xFF, 0xFF,
				},
				.y_area_scale_border = {
					0xFFF, 0xFFF,
				},
				.y_area_scale_clip_l = 0x1FF,
				.y_area_scale_clip_h = 0x1FF,
			}
		},
		[1] = {	// min
			.hpf_enable = 0,
			.flat_ctrl_enable = 0,
			.y_ctrl_enable = 0,
			.hpf_k = {
				0,	// 0
				0,	// 1
				0,	// 2
				0,	// 3
				0,	// 4
				0,	// 5
				0,	// 6
				0,	// 7
				0,	// 8
				0,	// 9
			},
			.hpf_level_clip_p = 0,
			.hpf_level_clip_m = 0,
			.flat_scale = 0,
			.flat_threshold = 0,
			.flat_gain_limit = 0,
			.flat_level_clip_p = 0,
			.flat_level_clip_m = 0,
			.y_convert_coef = {
				0, 0, 0,
				0, 0, 0,
				0, 0, 0,
			},
			.y_ctrl_offset = {
				0, 0, 0, 0,
			},
			.y_ctrl_gain = {
				0, 0, 0, 0,
			},
			.y_ctrl_border = {
				0, 0, 0, 0,
			},
			.y_ctrl_gain_posi_dec1 = 0,
			.y_ctrl_gain_posi_dec2 = 0,
			.y_ctrl_level_clip_p = 0,
			.y_ctrl_level_clip_m = 0,
			.y_ctrl_cor_p = 0,
			.y_ctrl_cor_m = 0,
			.hpf_add_level_clip_r = 0,
			.hpf_add_level_clip_g = 0,
			.hpf_add_level_clip_b = 0,
			.area_a_enable = 0,
			.area_b_enable = 0,
			.area_marge_method = 0,
			.area_a_ctrl = {
				.ellipse_area_focus1_x = 0,
				.ellipse_area_focus1_y = 0,
				.ellipse_area_focus2_x = 0,
				.ellipse_area_focus2_y = 0,
				.c_area_scale_offset = 0,
				.c_area_scale_gain = {
					0, 0,
				},
				.c_area_scale_border = 0,
				.c_area_scale_clip_l = 0,
				.c_area_scale_clip_h = 0,
				.y_area_scale_gain = {
					0, 0,
				},
				.y_area_scale_border = {
					0, 0,
				},
				.y_area_scale_clip_l = 0,
				.y_area_scale_clip_h = 0,
			},
			.area_b_ctrl = {
				.ellipse_area_focus1_x = 0,
				.ellipse_area_focus1_y = 0,
				.ellipse_area_focus2_x = 0,
				.ellipse_area_focus2_y = 0,
				.c_area_scale_offset = 0,
				.c_area_scale_gain = {
					0, 0,
				},
				.c_area_scale_border = 0,
				.c_area_scale_clip_l = 0,
				.c_area_scale_clip_h = 0,
				.y_area_scale_gain = {
					0, 0,
				},
				.y_area_scale_border = {
					0, 0,
				},
				.y_area_scale_clip_l = 0,
				.y_area_scale_clip_h = 0,
			}
		},
		[2] = {	// ind
			.hpf_enable = 1,
			.flat_ctrl_enable = 0,
			.y_ctrl_enable = 1,
			.hpf_k = {
				2,	// 0
				3,	// 1
				4,	// 2
				5,	// 3
				6,	// 4
				7,	// 5
				8,	// 6
				9,	// 7
				10,	// 8
				11,	// 9
			},
			.hpf_level_clip_p = 12,
			.hpf_level_clip_m = 13,
			.flat_scale = 14,
			.flat_threshold = 15,
			.flat_gain_limit = 16,
			.flat_level_clip_p = 17,
			.flat_level_clip_m = 18,
			.y_convert_coef = {
				19, 20, 21,
				22, 23, 24,
				25, 26, 27,
			},
			.y_ctrl_offset = {
				28, 29, 30, 31,
			},
			.y_ctrl_gain = {
				32, 33, 34, 35,
			},
			.y_ctrl_border = {
				36, 37, 38, 39,
			},
			.y_ctrl_gain_posi_dec1 = 2,
			.y_ctrl_gain_posi_dec2 = 3,
			.y_ctrl_level_clip_p = 42,
			.y_ctrl_level_clip_m = 43,
			.y_ctrl_cor_p = 44,
			.y_ctrl_cor_m = 45,
			.hpf_add_level_clip_r = 46,
			.hpf_add_level_clip_g = 47,
			.hpf_add_level_clip_b = 48,
			.area_a_enable = 1,
			.area_b_enable = 0,
			.area_marge_method = 1,
			.area_a_ctrl = {
				.ellipse_area_focus1_x = 49,
				.ellipse_area_focus1_y = 50,
				.ellipse_area_focus2_x = 51,
				.ellipse_area_focus2_y = 52,
				.c_area_scale_offset = 53,
				.c_area_scale_gain = {
					54, 55,
				},
				.c_area_scale_border = 56,
				.c_area_scale_clip_l = 57,
				.c_area_scale_clip_h = 58,
				.y_area_scale_gain = {
					59, 60,
				},
				.y_area_scale_border = {
					61, 62,
				},
				.y_area_scale_clip_l = 63,
				.y_area_scale_clip_h = 64,
			},
			.area_b_ctrl = {
				.ellipse_area_focus1_x = 65,
				.ellipse_area_focus1_y = 66,
				.ellipse_area_focus2_x = 67,
				.ellipse_area_focus2_y = 68,
				.c_area_scale_offset = 69,
				.c_area_scale_gain = {
					70, 71,
				},
				.c_area_scale_border = 72,
				.c_area_scale_clip_l = 73,
				.c_area_scale_clip_h = 74,
				.y_area_scale_gain = {
					75, 76,
				},
				.y_area_scale_border = {
					77, 78,
				},
				.y_area_scale_clip_l = 79,
				.y_area_scale_clip_h = 80,
			}
		},
	};
#ifdef CO_MSG_PRINT_ON
	kint32 ercd;
#endif
	kuint32 loopcnt;

	Ddim_Print(( "%s\n", D_IM_B2R_FUNC_NAME ));



	for( loopcnt = 0; loopcnt < (sizeof(b2r_ctrl_hpf) / sizeof(b2r_ctrl_hpf[0])); loopcnt++ ) {
		Ddim_Print(( "** %u\n", loopcnt ));

#ifdef CO_MSG_PRINT_ON
		ercd = Im_B2R_Ctrl_HighPassFilter( self->pipeNo, &b2r_ctrl_hpf[loopcnt] );
		Ddim_Print(( D_IM_B2R_FUNC_NAME "0x%x\n", ercd ));
		Im_B2R_On_Pclk( D_IM_B2R_PIPE12 );
		Ddim_Print(( "IO_B2R_P1.HFEEN          = 0x%x\n",    IO_B2R_P1.F_B2R.HFA.HFACTL.bit.HFEEN ));
		Ddim_Print(( "IO_B2R_P1.HFAFEN         = 0x%x\n",    IO_B2R_P1.F_B2R.HFA.HFACTL.bit.HFAFEN ));
		Ddim_Print(( "IO_B2R_P1.HFAYEN         = 0x%x\n",    IO_B2R_P1.F_B2R.HFA.HFACTL.bit.HFAYEN ));
		Ddim_Print(( "IO_B2R_P1.HFK[0]         = 0x%08lx\n", IO_B2R_P1.F_B2R.HFA.HFK.word[0] ));
		Ddim_Print(( "IO_B2R_P1.HFK[1]         = 0x%08lx\n", IO_B2R_P1.F_B2R.HFA.HFK.word[1] ));
		Ddim_Print(( "IO_B2R_P1.HFK[2]         = 0x%08lx\n", IO_B2R_P1.F_B2R.HFA.HFK.word[2] ));
		Ddim_Print(( "IO_B2R_P1.HFK[3]         = 0x%08lx\n", IO_B2R_P1.F_B2R.HFA.HFK.word[3] ));
		Ddim_Print(( "IO_B2R_P1.HFK0           = 0x%x\n",    IO_B2R_P1.F_B2R.HFA.HFK.bit.HFK0 ));
		Ddim_Print(( "IO_B2R_P1.HFK1           = 0x%x\n",    IO_B2R_P1.F_B2R.HFA.HFK.bit.HFK1 ));
		Ddim_Print(( "IO_B2R_P1.HFK2           = 0x%x\n",    IO_B2R_P1.F_B2R.HFA.HFK.bit.HFK2 ));
		Ddim_Print(( "IO_B2R_P1.HFK3           = 0x%x\n",    IO_B2R_P1.F_B2R.HFA.HFK.bit.HFK3 ));
		Ddim_Print(( "IO_B2R_P1.HFK4           = 0x%x\n",    IO_B2R_P1.F_B2R.HFA.HFK.bit.HFK4 ));
		Ddim_Print(( "IO_B2R_P1.HFK5           = 0x%x\n",    IO_B2R_P1.F_B2R.HFA.HFK.bit.HFK5 ));
		Ddim_Print(( "IO_B2R_P1.HFK6           = 0x%x\n",    IO_B2R_P1.F_B2R.HFA.HFK.bit.HFK6 ));
		Ddim_Print(( "IO_B2R_P1.HFK7           = 0x%x\n",    IO_B2R_P1.F_B2R.HFA.HFK.bit.HFK7 ));
		Ddim_Print(( "IO_B2R_P1.HFK8           = 0x%x\n",    IO_B2R_P1.F_B2R.HFA.HFK.bit.HFK8 ));
		Ddim_Print(( "IO_B2R_P1.HFK9           = 0x%x\n",    IO_B2R_P1.F_B2R.HFA.HFK.bit.HFK9 ));
		Ddim_Print(( "IO_B2R_P1.HFEFCLPP       = 0x%x\n",    IO_B2R_P1.F_B2R.HFA.HFEFCLP.bit.HFEFCLPP ));
		Ddim_Print(( "IO_B2R_P1.HFEFCLPM       = 0x%x\n",    IO_B2R_P1.F_B2R.HFA.HFEFCLP.bit.HFEFCLPM ));
		Ddim_Print(( "IO_B2R_P1.HFAFSL         = 0x%x\n",    IO_B2R_P1.F_B2R.HFA.HFAFST.bit.HFAFSL ));
		Ddim_Print(( "IO_B2R_P1.HFAFTH         = 0x%x\n",    IO_B2R_P1.F_B2R.HFA.HFAFST.bit.HFAFTH ));
		Ddim_Print(( "IO_B2R_P1.HFAFGU         = 0x%x\n",    IO_B2R_P1.F_B2R.HFA.HFAFGU.bit.HFAFGU ));
		Ddim_Print(( "IO_B2R_P1.HFAFCLPP       = 0x%x\n",    IO_B2R_P1.F_B2R.HFA.HFAFCLP.bit.HFAFCLPP ));
		Ddim_Print(( "IO_B2R_P1.HFAFCLPM       = 0x%x\n",    IO_B2R_P1.F_B2R.HFA.HFAFCLP.bit.HFAFCLPM ));
		Ddim_Print(( "IO_B2R_P1.HFAYC[0]       = 0x%lx\n",   IO_B2R_P1.F_B2R.HFA.HFAYC.word[0] ));
		Ddim_Print(( "IO_B2R_P1.HFAYC[1]       = 0x%lx\n",   IO_B2R_P1.F_B2R.HFA.HFAYC.word[1] ));
		Ddim_Print(( "IO_B2R_P1.HFAYC[2]       = 0x%lx\n",   IO_B2R_P1.F_B2R.HFA.HFAYC.word[2] ));
		Ddim_Print(( "IO_B2R_P1.HFAYC[3]       = 0x%lx\n",   IO_B2R_P1.F_B2R.HFA.HFAYC.word[3] ));
		Ddim_Print(( "IO_B2R_P1.HFAYC00        = 0x%x\n",    IO_B2R_P1.F_B2R.HFA.HFAYC.bit.HFAYC00 ));
		Ddim_Print(( "IO_B2R_P1.HFAYC01        = 0x%x\n",    IO_B2R_P1.F_B2R.HFA.HFAYC.bit.HFAYC01 ));
		Ddim_Print(( "IO_B2R_P1.HFAYC02        = 0x%x\n",    IO_B2R_P1.F_B2R.HFA.HFAYC.bit.HFAYC02 ));
		Ddim_Print(( "IO_B2R_P1.HFAYC10        = 0x%x\n",    IO_B2R_P1.F_B2R.HFA.HFAYC.bit.HFAYC10 ));
		Ddim_Print(( "IO_B2R_P1.HFAYC11        = 0x%x\n",    IO_B2R_P1.F_B2R.HFA.HFAYC.bit.HFAYC11 ));
		Ddim_Print(( "IO_B2R_P1.HFAYC12        = 0x%x\n",    IO_B2R_P1.F_B2R.HFA.HFAYC.bit.HFAYC12 ));
		Ddim_Print(( "IO_B2R_P1.HFAYC20        = 0x%x\n",    IO_B2R_P1.F_B2R.HFA.HFAYC.bit.HFAYC20 ));
		Ddim_Print(( "IO_B2R_P1.HFAYC21        = 0x%x\n",    IO_B2R_P1.F_B2R.HFA.HFAYC.bit.HFAYC21 ));
		Ddim_Print(( "IO_B2R_P1.HFAYC22        = 0x%x\n",    IO_B2R_P1.F_B2R.HFA.HFAYC.bit.HFAYC22 ));
		Ddim_Print(( "IO_B2R_P1.HFAYOF_0       = 0x%x\n",    IO_B2R_P1.F_B2R.HFA.HFAYOF.bit.HFAYOF_0 ));
		Ddim_Print(( "IO_B2R_P1.HFAYOF_1       = 0x%x\n",    IO_B2R_P1.F_B2R.HFA.HFAYOF.bit.HFAYOF_1 ));
		Ddim_Print(( "IO_B2R_P1.HFAYOF_2       = 0x%x\n",    IO_B2R_P1.F_B2R.HFA.HFAYOF.bit.HFAYOF_2 ));
		Ddim_Print(( "IO_B2R_P1.HFAYOF_3       = 0x%x\n",    IO_B2R_P1.F_B2R.HFA.HFAYOF.bit.HFAYOF_3 ));
		Ddim_Print(( "IO_B2R_P1.HFAYGA         = 0x%lx\n",   IO_B2R_P1.F_B2R.HFA.HFAYGA.word ));
		Ddim_Print(( "IO_B2R_P1.HFAYGA_0       = 0x%x\n",    IO_B2R_P1.F_B2R.HFA.HFAYGA.bit.HFAYGA_0 ));
		Ddim_Print(( "IO_B2R_P1.HFAYGA_1       = 0x%x\n",    IO_B2R_P1.F_B2R.HFA.HFAYGA.bit.HFAYGA_1 ));
		Ddim_Print(( "IO_B2R_P1.HFAYGA_2       = 0x%x\n",    IO_B2R_P1.F_B2R.HFA.HFAYGA.bit.HFAYGA_2 ));
		Ddim_Print(( "IO_B2R_P1.HFAYGA_3       = 0x%x\n",    IO_B2R_P1.F_B2R.HFA.HFAYGA.bit.HFAYGA_3 ));
		Ddim_Print(( "IO_B2R_P1.HFAYBD_0       = 0x%x\n",    IO_B2R_P1.F_B2R.HFA.HFAYBD.bit.HFAYBD_0 ));
		Ddim_Print(( "IO_B2R_P1.HFAYBD_1       = 0x%x\n",    IO_B2R_P1.F_B2R.HFA.HFAYBD.bit.HFAYBD_1 ));
		Ddim_Print(( "IO_B2R_P1.HFAYBD_2       = 0x%x\n",    IO_B2R_P1.F_B2R.HFA.HFAYBD.bit.HFAYBD_2 ));
		Ddim_Print(( "IO_B2R_P1.HFAYBD_3       = 0x%x\n",    IO_B2R_P1.F_B2R.HFA.HFAYBD.bit.HFAYBD_3 ));
		Ddim_Print(( "IO_B2R_P1.HFAYDIV1       = 0x%x\n",    IO_B2R_P1.F_B2R.HFA.HFAYDIV.bit.HFAYDIV1 ));
		Ddim_Print(( "IO_B2R_P1.HFAYDIV2       = 0x%x\n",    IO_B2R_P1.F_B2R.HFA.HFAYDIV.bit.HFAYDIV2 ));
		Ddim_Print(( "IO_B2R_P1.HFAYCLPP       = 0x%x\n",    IO_B2R_P1.F_B2R.HFA.HFAYCLP.bit.HFAYCLPP ));
		Ddim_Print(( "IO_B2R_P1.HFAYCLPM       = 0x%x\n",    IO_B2R_P1.F_B2R.HFA.HFAYCLP.bit.HFAYCLPM ));
		Ddim_Print(( "IO_B2R_P1.HFACORP        = 0x%x\n",    IO_B2R_P1.F_B2R.HFA.HFACOR.bit.HFACORP ));
		Ddim_Print(( "IO_B2R_P1.HFACORM        = 0x%x\n",    IO_B2R_P1.F_B2R.HFA.HFACOR.bit.HFACORM ));
		Ddim_Print(( "IO_B2R_P1.HFACLPR        = 0x%x\n",    IO_B2R_P1.F_B2R.HFA.HFACLP.bit.HFACLPR ));
		Ddim_Print(( "IO_B2R_P1.HFACLPG        = 0x%x\n",    IO_B2R_P1.F_B2R.HFA.HFACLP.bit.HFACLPG ));
		Ddim_Print(( "IO_B2R_P1.HFACLPB        = 0x%x\n",    IO_B2R_P1.F_B2R.HFA.HFACLP.bit.HFACLPB ));
		Ddim_Print(( "IO_B2R_P1.HFACAE         = 0x%x\n",    IO_B2R_P1.F_B2R.HFA.HFACRVCTL.bit.HFACAE ));
		Ddim_Print(( "IO_B2R_P1.HFACBE         = 0x%x\n",    IO_B2R_P1.F_B2R.HFA.HFACRVCTL.bit.HFACBE ));
		Ddim_Print(( "IO_B2R_P1.HFACRVMRG      = 0x%x\n",    IO_B2R_P1.F_B2R.HFA.HFACRVCTL.bit.HFACRVMRG ));
		Ddim_Print(( "IO_B2R_P1.HFACRVAFX      = 0x%lx\n",   IO_B2R_P1.F_B2R.HFA.HFACVAFX.word ));
		Ddim_Print(( "IO_B2R_P1.HFACRVAFX1     = 0x%x\n",    IO_B2R_P1.F_B2R.HFA.HFACVAFX.bit.HFACRVAFX1 ));
		Ddim_Print(( "IO_B2R_P1.HFACRVAFY1     = 0x%x\n",    IO_B2R_P1.F_B2R.HFA.HFACVAFX.bit.HFACRVAFY1 ));
		Ddim_Print(( "IO_B2R_P1.HFACRVAFX2     = 0x%x\n",    IO_B2R_P1.F_B2R.HFA.HFACVAFX.bit.HFACRVAFX2 ));
		Ddim_Print(( "IO_B2R_P1.HFACRVAFY2     = 0x%x\n",    IO_B2R_P1.F_B2R.HFA.HFACVAFX.bit.HFACRVAFY2 ));
		Ddim_Print(( "IO_B2R_P1.HFACRVASCLOF1  = 0x%x\n",    IO_B2R_P1.F_B2R.HFA.HFACRVASCLOF.bit.HFACRVASCLOF1 ));
		Ddim_Print(( "IO_B2R_P1.HFACRVASCLGA   = 0x%lx\n",   IO_B2R_P1.F_B2R.HFA.HFACRVASCLGA.word ));
		Ddim_Print(( "IO_B2R_P1.HFACRVASCLGA_0 = 0x%x\n",    IO_B2R_P1.F_B2R.HFA.HFACRVASCLGA.bit.HFACRVASCLGA_0 ));
		Ddim_Print(( "IO_B2R_P1.HFACRVASCLGA_1 = 0x%x\n",    IO_B2R_P1.F_B2R.HFA.HFACRVASCLGA.bit.HFACRVASCLGA_1 ));
		Ddim_Print(( "IO_B2R_P1.HFACRVASCLBD1  = 0x%x\n",    IO_B2R_P1.F_B2R.HFA.HFACRVASCLBD.bit.HFACRVASCLBD1 ));
		Ddim_Print(( "IO_B2R_P1.HFACRVASCLCPL  = 0x%x\n",    IO_B2R_P1.F_B2R.HFA.HFACRVASCLCP.bit.HFACRVASCLCPL ));
		Ddim_Print(( "IO_B2R_P1.HFACRVASCLCPH  = 0x%x\n",    IO_B2R_P1.F_B2R.HFA.HFACRVASCLCP.bit.HFACRVASCLCPH ));
		Ddim_Print(( "IO_B2R_P1.HFAYASCLGA_0   = 0x%x\n",    IO_B2R_P1.F_B2R.HFA.HFAYASCLGA.bit.HFAYASCLGA_0 ));
		Ddim_Print(( "IO_B2R_P1.HFAYASCLGA_1   = 0x%x\n",    IO_B2R_P1.F_B2R.HFA.HFAYASCLGA.bit.HFAYASCLGA_1 ));
		Ddim_Print(( "IO_B2R_P1.HFAYASCLBD_0   = 0x%x\n",    IO_B2R_P1.F_B2R.HFA.HFAYASCLBD.bit.HFAYASCLBD_0 ));
		Ddim_Print(( "IO_B2R_P1.HFAYASCLBD_1   = 0x%x\n",    IO_B2R_P1.F_B2R.HFA.HFAYASCLBD.bit.HFAYASCLBD_1 ));
		Ddim_Print(( "IO_B2R_P1.HFAYASCLCLPL   = 0x%x\n",    IO_B2R_P1.F_B2R.HFA.HFAYASCLCLP.bit.HFAYASCLCLPL ));
		Ddim_Print(( "IO_B2R_P1.HFAYASCLCLPH   = 0x%x\n",    IO_B2R_P1.F_B2R.HFA.HFAYASCLCLP.bit.HFAYASCLCLPH ));
		Ddim_Print(( "IO_B2R_P1.HFACRVBFX      = 0x%lx\n",   IO_B2R_P1.F_B2R.HFA.HFACVBFX.word ));
		Ddim_Print(( "IO_B2R_P1.HFACRVBFX1     = 0x%x\n",    IO_B2R_P1.F_B2R.HFA.HFACVBFX.bit.HFACRVBFX1 ));
		Ddim_Print(( "IO_B2R_P1.HFACRVBFY1     = 0x%x\n",    IO_B2R_P1.F_B2R.HFA.HFACVBFX.bit.HFACRVBFY1 ));
		Ddim_Print(( "IO_B2R_P1.HFACRVBFX2     = 0x%x\n",    IO_B2R_P1.F_B2R.HFA.HFACVBFX.bit.HFACRVBFX2 ));
		Ddim_Print(( "IO_B2R_P1.HFACRVBFY2     = 0x%x\n",    IO_B2R_P1.F_B2R.HFA.HFACVBFX.bit.HFACRVBFY2 ));
		Ddim_Print(( "IO_B2R_P1.HFACRVBSCLOF1  = 0x%x\n",    IO_B2R_P1.F_B2R.HFA.HFACRVBSCLOF.bit.HFACRVBSCLOF1 ));
		Ddim_Print(( "IO_B2R_P1.HFACRVBSCLGA   = 0x%lx\n",   IO_B2R_P1.F_B2R.HFA.HFACRVBSCLGA.word ));
		Ddim_Print(( "IO_B2R_P1.HFACRVBSCLGA_0 = 0x%x\n",    IO_B2R_P1.F_B2R.HFA.HFACRVBSCLGA.bit.HFACRVBSCLGA_0 ));
		Ddim_Print(( "IO_B2R_P1.HFACRVBSCLGA_1 = 0x%x\n",    IO_B2R_P1.F_B2R.HFA.HFACRVBSCLGA.bit.HFACRVBSCLGA_1 ));
		Ddim_Print(( "IO_B2R_P1.HFACRVBSCLBD1  = 0x%x\n",    IO_B2R_P1.F_B2R.HFA.HFACRVBSCLBD.bit.HFACRVBSCLBD1 ));
		Ddim_Print(( "IO_B2R_P1.HFACRVBSCLCPL  = 0x%x\n",    IO_B2R_P1.F_B2R.HFA.HFACRVBSCLCP.bit.HFACRVBSCLCPL ));
		Ddim_Print(( "IO_B2R_P1.HFACRVBSCLCPH  = 0x%x\n",    IO_B2R_P1.F_B2R.HFA.HFACRVBSCLCP.bit.HFACRVBSCLCPH ));
		Ddim_Print(( "IO_B2R_P1.HFAYBSCLGA_0   = 0x%x\n",    IO_B2R_P1.F_B2R.HFA.HFAYBSCLGA.bit.HFAYBSCLGA_0 ));
		Ddim_Print(( "IO_B2R_P1.HFAYBSCLGA_1   = 0x%x\n",    IO_B2R_P1.F_B2R.HFA.HFAYBSCLGA.bit.HFAYBSCLGA_1 ));
		Ddim_Print(( "IO_B2R_P1.HFAYBSCLBD_0   = 0x%x\n",    IO_B2R_P1.F_B2R.HFA.HFAYBSCLBD.bit.HFAYBSCLBD_0 ));
		Ddim_Print(( "IO_B2R_P1.HFAYBSCLBD_1   = 0x%x\n",    IO_B2R_P1.F_B2R.HFA.HFAYBSCLBD.bit.HFAYBSCLBD_1 ));
		Ddim_Print(( "IO_B2R_P1.HFAYBSCLCLPL   = 0x%x\n",    IO_B2R_P1.F_B2R.HFA.HFAYBSCLCLP.bit.HFAYBSCLCLPL ));
		Ddim_Print(( "IO_B2R_P1.HFAYBSCLCLPH   = 0x%x\n",    IO_B2R_P1.F_B2R.HFA.HFAYBSCLCLP.bit.HFAYBSCLCLPH ));
		Ddim_Print(( "IO_B2R_P2.HFEEN          = 0x%x\n",    IO_B2R_P2.F_B2R.HFA.HFACTL.bit.HFEEN ));
		Ddim_Print(( "IO_B2R_P2.HFAFEN         = 0x%x\n",    IO_B2R_P2.F_B2R.HFA.HFACTL.bit.HFAFEN ));
		Ddim_Print(( "IO_B2R_P2.HFAYEN         = 0x%x\n",    IO_B2R_P2.F_B2R.HFA.HFACTL.bit.HFAYEN ));
		Ddim_Print(( "IO_B2R_P2.HFK[0]         = 0x%08lx\n", IO_B2R_P2.F_B2R.HFA.HFK.word[0] ));
		Ddim_Print(( "IO_B2R_P2.HFK[1]         = 0x%08lx\n", IO_B2R_P2.F_B2R.HFA.HFK.word[1] ));
		Ddim_Print(( "IO_B2R_P2.HFK[2]         = 0x%08lx\n", IO_B2R_P2.F_B2R.HFA.HFK.word[2] ));
		Ddim_Print(( "IO_B2R_P2.HFK[3]         = 0x%08lx\n", IO_B2R_P2.F_B2R.HFA.HFK.word[3] ));
		Ddim_Print(( "IO_B2R_P2.HFK0           = 0x%x\n",    IO_B2R_P2.F_B2R.HFA.HFK.bit.HFK0 ));
		Ddim_Print(( "IO_B2R_P2.HFK1           = 0x%x\n",    IO_B2R_P2.F_B2R.HFA.HFK.bit.HFK1 ));
		Ddim_Print(( "IO_B2R_P2.HFK2           = 0x%x\n",    IO_B2R_P2.F_B2R.HFA.HFK.bit.HFK2 ));
		Ddim_Print(( "IO_B2R_P2.HFK3           = 0x%x\n",    IO_B2R_P2.F_B2R.HFA.HFK.bit.HFK3 ));
		Ddim_Print(( "IO_B2R_P2.HFK4           = 0x%x\n",    IO_B2R_P2.F_B2R.HFA.HFK.bit.HFK4 ));
		Ddim_Print(( "IO_B2R_P2.HFK5           = 0x%x\n",    IO_B2R_P2.F_B2R.HFA.HFK.bit.HFK5 ));
		Ddim_Print(( "IO_B2R_P2.HFK6           = 0x%x\n",    IO_B2R_P2.F_B2R.HFA.HFK.bit.HFK6 ));
		Ddim_Print(( "IO_B2R_P2.HFK7           = 0x%x\n",    IO_B2R_P2.F_B2R.HFA.HFK.bit.HFK7 ));
		Ddim_Print(( "IO_B2R_P2.HFK8           = 0x%x\n",    IO_B2R_P2.F_B2R.HFA.HFK.bit.HFK8 ));
		Ddim_Print(( "IO_B2R_P2.HFK9           = 0x%x\n",    IO_B2R_P2.F_B2R.HFA.HFK.bit.HFK9 ));
		Ddim_Print(( "IO_B2R_P2.HFEFCLPP       = 0x%x\n",    IO_B2R_P2.F_B2R.HFA.HFEFCLP.bit.HFEFCLPP ));
		Ddim_Print(( "IO_B2R_P2.HFEFCLPM       = 0x%x\n",    IO_B2R_P2.F_B2R.HFA.HFEFCLP.bit.HFEFCLPM ));
		Ddim_Print(( "IO_B2R_P2.HFAFSL         = 0x%x\n",    IO_B2R_P2.F_B2R.HFA.HFAFST.bit.HFAFSL ));
		Ddim_Print(( "IO_B2R_P2.HFAFTH         = 0x%x\n",    IO_B2R_P2.F_B2R.HFA.HFAFST.bit.HFAFTH ));
		Ddim_Print(( "IO_B2R_P2.HFAFGU         = 0x%x\n",    IO_B2R_P2.F_B2R.HFA.HFAFGU.bit.HFAFGU ));
		Ddim_Print(( "IO_B2R_P2.HFAFCLPP       = 0x%x\n",    IO_B2R_P2.F_B2R.HFA.HFAFCLP.bit.HFAFCLPP ));
		Ddim_Print(( "IO_B2R_P2.HFAFCLPM       = 0x%x\n",    IO_B2R_P2.F_B2R.HFA.HFAFCLP.bit.HFAFCLPM ));
		Ddim_Print(( "IO_B2R_P2.HFAYC[0]       = 0x%lx\n",   IO_B2R_P2.F_B2R.HFA.HFAYC.word[0] ));
		Ddim_Print(( "IO_B2R_P2.HFAYC[1]       = 0x%lx\n",   IO_B2R_P2.F_B2R.HFA.HFAYC.word[1] ));
		Ddim_Print(( "IO_B2R_P2.HFAYC[2]       = 0x%lx\n",   IO_B2R_P2.F_B2R.HFA.HFAYC.word[2] ));
		Ddim_Print(( "IO_B2R_P2.HFAYC[3]       = 0x%lx\n",   IO_B2R_P2.F_B2R.HFA.HFAYC.word[3] ));
		Ddim_Print(( "IO_B2R_P2.HFAYC00        = 0x%x\n",    IO_B2R_P2.F_B2R.HFA.HFAYC.bit.HFAYC00 ));
		Ddim_Print(( "IO_B2R_P2.HFAYC01        = 0x%x\n",    IO_B2R_P2.F_B2R.HFA.HFAYC.bit.HFAYC01 ));
		Ddim_Print(( "IO_B2R_P2.HFAYC02        = 0x%x\n",    IO_B2R_P2.F_B2R.HFA.HFAYC.bit.HFAYC02 ));
		Ddim_Print(( "IO_B2R_P2.HFAYC10        = 0x%x\n",    IO_B2R_P2.F_B2R.HFA.HFAYC.bit.HFAYC10 ));
		Ddim_Print(( "IO_B2R_P2.HFAYC11        = 0x%x\n",    IO_B2R_P2.F_B2R.HFA.HFAYC.bit.HFAYC11 ));
		Ddim_Print(( "IO_B2R_P2.HFAYC12        = 0x%x\n",    IO_B2R_P2.F_B2R.HFA.HFAYC.bit.HFAYC12 ));
		Ddim_Print(( "IO_B2R_P2.HFAYC20        = 0x%x\n",    IO_B2R_P2.F_B2R.HFA.HFAYC.bit.HFAYC20 ));
		Ddim_Print(( "IO_B2R_P2.HFAYC21        = 0x%x\n",    IO_B2R_P2.F_B2R.HFA.HFAYC.bit.HFAYC21 ));
		Ddim_Print(( "IO_B2R_P2.HFAYC22        = 0x%x\n",    IO_B2R_P2.F_B2R.HFA.HFAYC.bit.HFAYC22 ));
		Ddim_Print(( "IO_B2R_P2.HFAYOF_0       = 0x%x\n",    IO_B2R_P2.F_B2R.HFA.HFAYOF.bit.HFAYOF_0 ));
		Ddim_Print(( "IO_B2R_P2.HFAYOF_1       = 0x%x\n",    IO_B2R_P2.F_B2R.HFA.HFAYOF.bit.HFAYOF_1 ));
		Ddim_Print(( "IO_B2R_P2.HFAYOF_2       = 0x%x\n",    IO_B2R_P2.F_B2R.HFA.HFAYOF.bit.HFAYOF_2 ));
		Ddim_Print(( "IO_B2R_P2.HFAYOF_3       = 0x%x\n",    IO_B2R_P2.F_B2R.HFA.HFAYOF.bit.HFAYOF_3 ));
		Ddim_Print(( "IO_B2R_P2.HFAYGA         = 0x%lx\n",   IO_B2R_P2.F_B2R.HFA.HFAYGA.word ));
		Ddim_Print(( "IO_B2R_P2.HFAYGA_0       = 0x%x\n",    IO_B2R_P2.F_B2R.HFA.HFAYGA.bit.HFAYGA_0 ));
		Ddim_Print(( "IO_B2R_P2.HFAYGA_1       = 0x%x\n",    IO_B2R_P2.F_B2R.HFA.HFAYGA.bit.HFAYGA_1 ));
		Ddim_Print(( "IO_B2R_P2.HFAYGA_2       = 0x%x\n",    IO_B2R_P2.F_B2R.HFA.HFAYGA.bit.HFAYGA_2 ));
		Ddim_Print(( "IO_B2R_P2.HFAYGA_3       = 0x%x\n",    IO_B2R_P2.F_B2R.HFA.HFAYGA.bit.HFAYGA_3 ));
		Ddim_Print(( "IO_B2R_P2.HFAYBD_0       = 0x%x\n",    IO_B2R_P2.F_B2R.HFA.HFAYBD.bit.HFAYBD_0 ));
		Ddim_Print(( "IO_B2R_P2.HFAYBD_1       = 0x%x\n",    IO_B2R_P2.F_B2R.HFA.HFAYBD.bit.HFAYBD_1 ));
		Ddim_Print(( "IO_B2R_P2.HFAYBD_2       = 0x%x\n",    IO_B2R_P2.F_B2R.HFA.HFAYBD.bit.HFAYBD_2 ));
		Ddim_Print(( "IO_B2R_P2.HFAYBD_3       = 0x%x\n",    IO_B2R_P2.F_B2R.HFA.HFAYBD.bit.HFAYBD_3 ));
		Ddim_Print(( "IO_B2R_P2.HFAYDIV1       = 0x%x\n",    IO_B2R_P2.F_B2R.HFA.HFAYDIV.bit.HFAYDIV1 ));
		Ddim_Print(( "IO_B2R_P2.HFAYDIV2       = 0x%x\n",    IO_B2R_P2.F_B2R.HFA.HFAYDIV.bit.HFAYDIV2 ));
		Ddim_Print(( "IO_B2R_P2.HFAYCLPP       = 0x%x\n",    IO_B2R_P2.F_B2R.HFA.HFAYCLP.bit.HFAYCLPP ));
		Ddim_Print(( "IO_B2R_P2.HFAYCLPM       = 0x%x\n",    IO_B2R_P2.F_B2R.HFA.HFAYCLP.bit.HFAYCLPM ));
		Ddim_Print(( "IO_B2R_P2.HFACORP        = 0x%x\n",    IO_B2R_P2.F_B2R.HFA.HFACOR.bit.HFACORP ));
		Ddim_Print(( "IO_B2R_P2.HFACORM        = 0x%x\n",    IO_B2R_P2.F_B2R.HFA.HFACOR.bit.HFACORM ));
		Ddim_Print(( "IO_B2R_P2.HFACLPR        = 0x%x\n",    IO_B2R_P2.F_B2R.HFA.HFACLP.bit.HFACLPR ));
		Ddim_Print(( "IO_B2R_P2.HFACLPG        = 0x%x\n",    IO_B2R_P2.F_B2R.HFA.HFACLP.bit.HFACLPG ));
		Ddim_Print(( "IO_B2R_P2.HFACLPB        = 0x%x\n",    IO_B2R_P2.F_B2R.HFA.HFACLP.bit.HFACLPB ));
		Ddim_Print(( "IO_B2R_P2.HFACAE         = 0x%x\n",    IO_B2R_P2.F_B2R.HFA.HFACRVCTL.bit.HFACAE ));
		Ddim_Print(( "IO_B2R_P2.HFACBE         = 0x%x\n",    IO_B2R_P2.F_B2R.HFA.HFACRVCTL.bit.HFACBE ));
		Ddim_Print(( "IO_B2R_P2.HFACRVMRG      = 0x%x\n",    IO_B2R_P2.F_B2R.HFA.HFACRVCTL.bit.HFACRVMRG ));
		Ddim_Print(( "IO_B2R_P2.HFACRVAFX      = 0x%lx\n",   IO_B2R_P2.F_B2R.HFA.HFACVAFX.word ));
		Ddim_Print(( "IO_B2R_P2.HFACRVAFX1     = 0x%x\n",    IO_B2R_P2.F_B2R.HFA.HFACVAFX.bit.HFACRVAFX1 ));
		Ddim_Print(( "IO_B2R_P2.HFACRVAFY1     = 0x%x\n",    IO_B2R_P2.F_B2R.HFA.HFACVAFX.bit.HFACRVAFY1 ));
		Ddim_Print(( "IO_B2R_P2.HFACRVAFX2     = 0x%x\n",    IO_B2R_P2.F_B2R.HFA.HFACVAFX.bit.HFACRVAFX2 ));
		Ddim_Print(( "IO_B2R_P2.HFACRVAFY2     = 0x%x\n",    IO_B2R_P2.F_B2R.HFA.HFACVAFX.bit.HFACRVAFY2 ));
		Ddim_Print(( "IO_B2R_P2.HFACRVASCLOF1  = 0x%x\n",    IO_B2R_P2.F_B2R.HFA.HFACRVASCLOF.bit.HFACRVASCLOF1 ));
		Ddim_Print(( "IO_B2R_P2.HFACRVASCLGA   = 0x%lx\n",   IO_B2R_P2.F_B2R.HFA.HFACRVASCLGA.word ));
		Ddim_Print(( "IO_B2R_P2.HFACRVASCLGA_0 = 0x%x\n",    IO_B2R_P2.F_B2R.HFA.HFACRVASCLGA.bit.HFACRVASCLGA_0 ));
		Ddim_Print(( "IO_B2R_P2.HFACRVASCLGA_1 = 0x%x\n",    IO_B2R_P2.F_B2R.HFA.HFACRVASCLGA.bit.HFACRVASCLGA_1 ));
		Ddim_Print(( "IO_B2R_P2.HFACRVASCLBD1  = 0x%x\n",    IO_B2R_P2.F_B2R.HFA.HFACRVASCLBD.bit.HFACRVASCLBD1 ));
		Ddim_Print(( "IO_B2R_P2.HFACRVASCLCPL  = 0x%x\n",    IO_B2R_P2.F_B2R.HFA.HFACRVASCLCP.bit.HFACRVASCLCPL ));
		Ddim_Print(( "IO_B2R_P2.HFACRVASCLCPH  = 0x%x\n",    IO_B2R_P2.F_B2R.HFA.HFACRVASCLCP.bit.HFACRVASCLCPH ));
		Ddim_Print(( "IO_B2R_P2.HFAYASCLGA_0   = 0x%x\n",    IO_B2R_P2.F_B2R.HFA.HFAYASCLGA.bit.HFAYASCLGA_0 ));
		Ddim_Print(( "IO_B2R_P2.HFAYASCLGA_1   = 0x%x\n",    IO_B2R_P2.F_B2R.HFA.HFAYASCLGA.bit.HFAYASCLGA_1 ));
		Ddim_Print(( "IO_B2R_P2.HFAYASCLBD_0   = 0x%x\n",    IO_B2R_P2.F_B2R.HFA.HFAYASCLBD.bit.HFAYASCLBD_0 ));
		Ddim_Print(( "IO_B2R_P2.HFAYASCLBD_1   = 0x%x\n",    IO_B2R_P2.F_B2R.HFA.HFAYASCLBD.bit.HFAYASCLBD_1 ));
		Ddim_Print(( "IO_B2R_P2.HFAYASCLCLPL   = 0x%x\n",    IO_B2R_P2.F_B2R.HFA.HFAYASCLCLP.bit.HFAYASCLCLPL ));
		Ddim_Print(( "IO_B2R_P2.HFAYASCLCLPH   = 0x%x\n",    IO_B2R_P2.F_B2R.HFA.HFAYASCLCLP.bit.HFAYASCLCLPH ));
		Ddim_Print(( "IO_B2R_P2.HFACRVBFX      = 0x%lx\n",   IO_B2R_P2.F_B2R.HFA.HFACVBFX.word ));
		Ddim_Print(( "IO_B2R_P2.HFACRVBFX1     = 0x%x\n",    IO_B2R_P2.F_B2R.HFA.HFACVBFX.bit.HFACRVBFX1 ));
		Ddim_Print(( "IO_B2R_P2.HFACRVBFY1     = 0x%x\n",    IO_B2R_P2.F_B2R.HFA.HFACVBFX.bit.HFACRVBFY1 ));
		Ddim_Print(( "IO_B2R_P2.HFACRVBFX2     = 0x%x\n",    IO_B2R_P2.F_B2R.HFA.HFACVBFX.bit.HFACRVBFX2 ));
		Ddim_Print(( "IO_B2R_P2.HFACRVBFY2     = 0x%x\n",    IO_B2R_P2.F_B2R.HFA.HFACVBFX.bit.HFACRVBFY2 ));
		Ddim_Print(( "IO_B2R_P2.HFACRVBSCLOF1  = 0x%x\n",    IO_B2R_P2.F_B2R.HFA.HFACRVBSCLOF.bit.HFACRVBSCLOF1 ));
		Ddim_Print(( "IO_B2R_P2.HFACRVBSCLGA   = 0x%lx\n",   IO_B2R_P2.F_B2R.HFA.HFACRVBSCLGA.word ));
		Ddim_Print(( "IO_B2R_P2.HFACRVBSCLGA_0 = 0x%x\n",    IO_B2R_P2.F_B2R.HFA.HFACRVBSCLGA.bit.HFACRVBSCLGA_0 ));
		Ddim_Print(( "IO_B2R_P2.HFACRVBSCLGA_1 = 0x%x\n",    IO_B2R_P2.F_B2R.HFA.HFACRVBSCLGA.bit.HFACRVBSCLGA_1 ));
		Ddim_Print(( "IO_B2R_P2.HFACRVBSCLBD1  = 0x%x\n",    IO_B2R_P2.F_B2R.HFA.HFACRVBSCLBD.bit.HFACRVBSCLBD1 ));
		Ddim_Print(( "IO_B2R_P2.HFACRVBSCLCPL  = 0x%x\n",    IO_B2R_P2.F_B2R.HFA.HFACRVBSCLCP.bit.HFACRVBSCLCPL ));
		Ddim_Print(( "IO_B2R_P2.HFACRVBSCLCPH  = 0x%x\n",    IO_B2R_P2.F_B2R.HFA.HFACRVBSCLCP.bit.HFACRVBSCLCPH ));
		Ddim_Print(( "IO_B2R_P2.HFAYBSCLGA_0   = 0x%x\n",    IO_B2R_P2.F_B2R.HFA.HFAYBSCLGA.bit.HFAYBSCLGA_0 ));
		Ddim_Print(( "IO_B2R_P2.HFAYBSCLGA_1   = 0x%x\n",    IO_B2R_P2.F_B2R.HFA.HFAYBSCLGA.bit.HFAYBSCLGA_1 ));
		Ddim_Print(( "IO_B2R_P2.HFAYBSCLBD_0   = 0x%x\n",    IO_B2R_P2.F_B2R.HFA.HFAYBSCLBD.bit.HFAYBSCLBD_0 ));
		Ddim_Print(( "IO_B2R_P2.HFAYBSCLBD_1   = 0x%x\n",    IO_B2R_P2.F_B2R.HFA.HFAYBSCLBD.bit.HFAYBSCLBD_1 ));
		Ddim_Print(( "IO_B2R_P2.HFAYBSCLCLPL   = 0x%x\n",    IO_B2R_P2.F_B2R.HFA.HFAYBSCLCLP.bit.HFAYBSCLCLPL ));
		Ddim_Print(( "IO_B2R_P2.HFAYBSCLCLPH   = 0x%x\n",    IO_B2R_P2.F_B2R.HFA.HFAYBSCLCLP.bit.HFAYBSCLCLPH ));
		Im_B2R_Off_Pclk( D_IM_B2R_PIPE12 );
#endif
	}

	return D_DDIM_OK;
}


CtImB2r4* ct_im_b2r4_new(void) 
{
    CtImB2r4 *self = k_object_new_with_private(CT_TYPE_IM_B2R4, sizeof(CtImB2r4Private));
    return self;
}
